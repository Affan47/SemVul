handle_mq(struct c2_dev *c2dev, u32 mq_index)
{
	if (c2dev->qptr_array[mq_index] == NULL) {
		pr_debug("handle_mq: stray activity for mq_index=%d\n",
			 mq_index);
		return;
	}

	switch (mq_index) {
	case (0):


		wake_up(&c2dev->req_vq_wo);
		break;
	case (1):
		handle_vq(c2dev, mq_index);
		break;
	case (2):


		handle_vq(c2dev, 1);

		c2_ae_event(c2dev, mq_index);
		break;
	default:


		c2_cq_event(c2dev, mq_index);
		break;
	}

	return;
}
