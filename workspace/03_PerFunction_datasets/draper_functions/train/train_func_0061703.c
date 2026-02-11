do_gmbus_xfer(struct i2c_adapter *adapter, struct i2c_msg *msgs, int num)
{
	struct intel_gmbus *bus = container_of(adapter,
					       struct intel_gmbus,
					       adapter);
	struct drm_i915_private *dev_priv = bus->dev_priv;
	int i = 0, inc, try = 0;
	int ret = 0;

retry:
	I915_WRITE(GMBUS0, bus->reg0);

	for (; i < num; i += inc) {
		inc = 1;
		if (gmbus_is_index_read(msgs, i, num)) {
			ret = gmbus_xfer_index_read(dev_priv, &msgs[i]);
			inc = 2;
		} else if (msgs[i].flags & I2C_M_RD) {
			ret = gmbus_xfer_read(dev_priv, &msgs[i], 0);
		} else {
			ret = gmbus_xfer_write(dev_priv, &msgs[i]);
		}

		if (!ret)
			ret = gmbus_wait_hw_status(dev_priv, GMBUS_HW_WAIT_PHASE,
						   GMBUS_HW_WAIT_EN);
		if (ret == -ETIMEDOUT)
			goto timeout;
		else if (ret)
			goto clear_err;
	}


	I915_WRITE(GMBUS1, GMBUS_CYCLE_STOP | GMBUS_SW_RDY);


	if (gmbus_wait_idle(dev_priv)) {
		DRM_DEBUG_KMS("GMBUS [%s] timed out waiting for idle\n",
			 adapter->name);
		ret = -ETIMEDOUT;
	}
	I915_WRITE(GMBUS0, 0);
	ret = ret ?: i;
	goto out;

clear_err:


	ret = -ENXIO;
	if (gmbus_wait_idle(dev_priv)) {
		DRM_DEBUG_KMS("GMBUS [%s] timed out after NAK\n",
			      adapter->name);
		ret = -ETIMEDOUT;
	}


	I915_WRITE(GMBUS1, GMBUS_SW_CLR_INT);
	I915_WRITE(GMBUS1, 0);
	I915_WRITE(GMBUS0, 0);

	DRM_DEBUG_KMS("GMBUS [%s] NAK for addr: %04x %c(%d)\n",
			 adapter->name, msgs[i].addr,
			 (msgs[i].flags & I2C_M_RD) ? 'r' : 'w', msgs[i].len);


	if (ret == -ENXIO && i == 0 && try++ == 0) {
		DRM_DEBUG_KMS("GMBUS [%s] NAK on first message, retry\n",
			      adapter->name);
		goto retry;
	}

	goto out;

timeout:
	DRM_DEBUG_KMS("GMBUS [%s] timed out, falling back to bit banging on pin %d\n",
		      bus->adapter.name, bus->reg0 & 0xff);
	I915_WRITE(GMBUS0, 0);


	ret = -EAGAIN;

out:
	return ret;
}
