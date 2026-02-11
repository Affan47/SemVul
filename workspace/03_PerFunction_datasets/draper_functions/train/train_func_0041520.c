c2_post_receive(struct ib_qp *ibqp, struct ib_recv_wr *ib_wr,
		    struct ib_recv_wr **bad_wr)
{
	struct c2_dev *c2dev = to_c2dev(ibqp->device);
	struct c2_qp *qp = to_c2qp(ibqp);
	union c2wr wr;
	unsigned long lock_flags;
	int err = 0;

	if (qp->state > IB_QPS_RTS) {
		err = -EINVAL;
		goto out;
	}


	while (ib_wr) {
		u32 tot_len;
		u8 actual_sge_count;

		if (ib_wr->num_sge > qp->recv_sgl_depth) {
			err = -EINVAL;
			break;
		}


		wr.rqwr.rq_hdr.user_hdr.hdr.context = ib_wr->wr_id;
		c2_wr_set_id(&wr, CCWR_RECV);
		c2_wr_set_flags(&wr, 0);


		BUG_ON(ib_wr->num_sge >= 256);
		err = move_sgl((struct c2_data_addr *) & (wr.rqwr.data),
			       ib_wr->sg_list,
			       ib_wr->num_sge, &tot_len, &actual_sge_count);
		c2_wr_set_sge_count(&wr, actual_sge_count);


		if (err) {
			break;
		}

		spin_lock_irqsave(&qp->lock, lock_flags);
		err = qp_wr_post(&qp->rq_mq, &wr, qp, qp->rq_mq.msg_size);
		if (err) {
			spin_unlock_irqrestore(&qp->lock, lock_flags);
			break;
		}


		c2_activity(c2dev, qp->rq_mq.index, qp->rq_mq.hint_count);
		spin_unlock_irqrestore(&qp->lock, lock_flags);

		ib_wr = ib_wr->next;
	}

out:
	if (err)
		*bad_wr = ib_wr;
	return err;
}
