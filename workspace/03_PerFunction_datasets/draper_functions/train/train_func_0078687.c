detach_free_fields(struct mailimf_orig_date * date,
			       struct mailimf_from * from,
			       struct mailimf_sender * sender,
			       struct mailimf_reply_to * reply_to,
			       struct mailimf_to * to,
			       struct mailimf_cc * cc,
			       struct mailimf_bcc * bcc,
			       struct mailimf_message_id * msg_id,
			       struct mailimf_in_reply_to * in_reply_to,
			       struct mailimf_references * references,
			       struct mailimf_subject * subject)
{
  detach_free_common_fields(date,
      from,
      sender,
      to,
      cc,
      bcc,
      msg_id);

  if (reply_to != NULL) {
    reply_to->rt_addr_list = NULL;
    mailimf_reply_to_free(reply_to);
  }

  if (in_reply_to != NULL) {
    in_reply_to->mid_list = NULL;
    mailimf_in_reply_to_free(in_reply_to);
  }

  if (references != NULL) {
    references->mid_list = NULL;
    mailimf_references_free(references);
  }

  if (subject != NULL) {
    subject->sbj_value = NULL;
    mailimf_subject_free(subject);
  }
}
