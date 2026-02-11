aac_src_notify_adapter(struct aac_dev *dev, u32 event)
{
	switch (event) {

	case AdapNormCmdQue:
		src_writel(dev, MUnit.ODR_C,
			INBOUNDDOORBELL_1 << SRC_ODR_SHIFT);
		break;
	case HostNormRespNotFull:
		src_writel(dev, MUnit.ODR_C,
			INBOUNDDOORBELL_4 << SRC_ODR_SHIFT);
		break;
	case AdapNormRespQue:
		src_writel(dev, MUnit.ODR_C,
			INBOUNDDOORBELL_2 << SRC_ODR_SHIFT);
		break;
	case HostNormCmdNotFull:
		src_writel(dev, MUnit.ODR_C,
			INBOUNDDOORBELL_3 << SRC_ODR_SHIFT);
		break;
	case FastIo:
		src_writel(dev, MUnit.ODR_C,
			INBOUNDDOORBELL_6 << SRC_ODR_SHIFT);
		break;
	case AdapPrintfDone:
		src_writel(dev, MUnit.ODR_C,
			INBOUNDDOORBELL_5 << SRC_ODR_SHIFT);
		break;
	default:
		BUG();
		break;
	}
}
