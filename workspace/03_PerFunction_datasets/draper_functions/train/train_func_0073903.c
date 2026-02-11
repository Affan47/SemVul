intel_init_emon(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	u32 lcfuse;
	u8 pxw[16];
	int i;


	I915_WRITE(ECR, 0);
	POSTING_READ(ECR);


	I915_WRITE(SDEW, 0x15040d00);
	I915_WRITE(CSIEW0, 0x007f0000);
	I915_WRITE(CSIEW1, 0x1e220004);
	I915_WRITE(CSIEW2, 0x04000004);

	for (i = 0; i < 5; i++)
		I915_WRITE(PEW(i), 0);
	for (i = 0; i < 3; i++)
		I915_WRITE(DEW(i), 0);


	for (i = 0; i < 16; i++) {
		u32 pxvidfreq = I915_READ(PXVFREQ(i));
		unsigned long freq = intel_pxfreq(pxvidfreq);
		unsigned long vid = (pxvidfreq & PXVFREQ_PX_MASK) >>
			PXVFREQ_PX_SHIFT;
		unsigned long val;

		val = vid * vid;
		val *= (freq / 1000);
		val *= 255;
		val /= (127*127*900);
		if (val > 0xff)
			DRM_ERROR("bad pxval: %ld\n", val);
		pxw[i] = val;
	}

	pxw[14] = 0;
	pxw[15] = 0;

	for (i = 0; i < 4; i++) {
		u32 val = (pxw[i*4] << 24) | (pxw[(i*4)+1] << 16) |
			(pxw[(i*4)+2] << 8) | (pxw[(i*4)+3]);
		I915_WRITE(PXW(i), val);
	}


	I915_WRITE(OGW0, 0);
	I915_WRITE(OGW1, 0);
	I915_WRITE(EG0, 0x00007f00);
	I915_WRITE(EG1, 0x0000000e);
	I915_WRITE(EG2, 0x000e0000);
	I915_WRITE(EG3, 0x68000300);
	I915_WRITE(EG4, 0x42000000);
	I915_WRITE(EG5, 0x00140031);
	I915_WRITE(EG6, 0);
	I915_WRITE(EG7, 0);

	for (i = 0; i < 8; i++)
		I915_WRITE(PXWL(i), 0);


	I915_WRITE(ECR, 0x80000019);

	lcfuse = I915_READ(LCFUSE02);

	dev_priv->ips.corr = (lcfuse & LCFUSE_HIV_MASK);
}
