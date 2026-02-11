handle_collision(private_child_rekey_t *this)
{
	child_sa_t *to_delete;

	if (this->collision->get_type(this->collision) == TASK_CHILD_REKEY)
	{
		chunk_t this_nonce, other_nonce;
		private_child_rekey_t *other = (private_child_rekey_t*)this->collision;

		this_nonce = this->child_create->get_lower_nonce(this->child_create);
		other_nonce = other->child_create->get_lower_nonce(other->child_create);


		if (memcmp(this_nonce.ptr, other_nonce.ptr,
				   min(this_nonce.len, other_nonce.len)) > 0)
		{
			child_sa_t *child_sa;

			DBG1(DBG_IKE, "CHILD_SA rekey collision won, deleting old child");
			to_delete = this->child_sa;

			if (!this->other_child_destroyed)
			{

				child_sa = other->child_create->get_child(other->child_create);
				if (child_sa)
				{
					child_sa->set_close_action(child_sa, ACTION_NONE);
				}
			}
		}
		else
		{
			DBG1(DBG_IKE, "CHILD_SA rekey collision lost, "
				 "deleting rekeyed child");
			to_delete = this->child_create->get_child(this->child_create);
		}
	}
	else
	{
		child_delete_t *del = (child_delete_t*)this->collision;


		if (del->get_child(del) != this->child_sa)
		{
			DBG1(DBG_IKE, "CHILD_SA rekey/delete collision, "
				 "deleting rekeyed child");
			to_delete = this->child_sa;
		}
		else
		{
			DBG1(DBG_IKE, "CHILD_SA rekey/delete collision, "
				 "deleting redundant child");
			to_delete = this->child_create->get_child(this->child_create);
		}
	}
	return to_delete;
}
