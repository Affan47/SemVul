WaitForDoorbellInt(MPT_ADAPTER *ioc, int howlong, int sleepFlag)
{
	int cntdn;
	int count = 0;
	u32 intstat=0;

	cntdn = 1000 * howlong;
	if (sleepFlag == CAN_SLEEP) {
		while (--cntdn) {
			intstat = CHIPREG_READ32(&ioc->chip->IntStatus);
			if (intstat & MPI_HIS_DOORBELL_INTERRUPT)
				break;
			msleep(1);
			count++;
		}
	} else {
		while (--cntdn) {
			intstat = CHIPREG_READ32(&ioc->chip->IntStatus);
			if (intstat & MPI_HIS_DOORBELL_INTERRUPT)
				break;
			udelay (1000);
			count++;
		}
	}

	if (cntdn) {
		dprintk(ioc, printk(MYIOC_s_DEBUG_FMT "WaitForDoorbell INT (cnt=%d) howlong=%d\n",
				ioc->name, count, howlong));
		return count;
	}

	printk(MYIOC_s_ERR_FMT "Doorbell INT timeout (count=%d), IntStatus=%x!\n",
			ioc->name, count, intstat);
	return -1;
}
