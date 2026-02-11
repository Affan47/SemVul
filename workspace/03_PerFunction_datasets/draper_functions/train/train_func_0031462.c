net2272_present(struct net2272 *dev)
{


	unsigned int ii;
	u8 val, refval;


	refval = net2272_read(dev, SCRATCH);
	for (ii = 0; ii < 0x100; ii += 7) {
		net2272_write(dev, SCRATCH, ii);
		val = net2272_read(dev, SCRATCH);
		if (val != ii) {
			dev_dbg(dev->dev,
				"%s: write/read SCRATCH register test failed: "
				"wrote:0x%2.2x, read:0x%2.2x\n",
				__func__, ii, val);
			return -EINVAL;
		}
	}

	net2272_write(dev, SCRATCH, refval);


	refval = net2272_read(dev, CHIPREV_2272);
	for (ii = 0; ii < 0x100; ii += 7) {
		net2272_write(dev, CHIPREV_2272, ii);
		val = net2272_read(dev, CHIPREV_2272);
		if (val != refval) {
			dev_dbg(dev->dev,
				"%s: write/read CHIPREV register test failed: "
				"wrote 0x%2.2x, read:0x%2.2x expected:0x%2.2x\n",
				__func__, ii, val, refval);
			return -EINVAL;
		}
	}


	val = net2272_read(dev, CHIPREV_LEGACY);
	if (val != NET2270_LEGACY_REV) {


		dev_dbg(dev->dev,
			"%s: WARNING: UNEXPECTED NET2272 LEGACY REGISTER VALUE:\n"
			" - CHIPREV_LEGACY: expected 0x%2.2x, got:0x%2.2x. (Not NET2272?)\n",
			__func__, NET2270_LEGACY_REV, val);
		return -EINVAL;
	}


	val = net2272_read(dev, CHIPREV_2272);
	switch (val) {
	case CHIPREV_NET2272_R1:


		dev_dbg(dev->dev,
			"%s: Rev 1 detected: newer silicon recommended for DMA support\n",
			__func__);
		break;
	case CHIPREV_NET2272_R1A:
		break;
	default:

		dev_dbg(dev->dev,
			"%s: unexpected silicon revision register value: "
			" CHIPREV_2272: 0x%2.2x\n",
			__func__, val);


	}


	return 0;
}
