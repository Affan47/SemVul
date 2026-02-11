set_mailmessage_flag(struct mail_msg_t* m,int flag)
{
if (m == NULL)
	ERROR_ABORT("mailmessage is NULL\n");
m->flags |= flag;
}
