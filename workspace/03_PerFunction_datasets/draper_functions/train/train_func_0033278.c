spk_msg_set(enum msg_index_t index, char *text, size_t length)
{
	int rc = 0;
	char *newstr = NULL;
	unsigned long flags;

	if ((index >= MSG_FIRST_INDEX) && (index < MSG_LAST_INDEX)) {
		newstr = kmalloc(length + 1, GFP_KERNEL);
		if (newstr) {
			memcpy(newstr, text, length);
			newstr[length] = '\0';
			if ((index >= MSG_FORMATTED_START
			&& index <= MSG_FORMATTED_END)
				&& !fmt_validate(speakup_default_msgs[index],
				newstr)) {
				kfree(newstr);
				return -EINVAL;
			}
			spin_lock_irqsave(&speakup_info.spinlock, flags);
			if (speakup_msgs[index] != speakup_default_msgs[index])
				kfree(speakup_msgs[index]);
			speakup_msgs[index] = newstr;
			spin_unlock_irqrestore(&speakup_info.spinlock, flags);
		} else {
			rc = -ENOMEM;
		}
	} else {
		rc = -EINVAL;
	}
	return rc;
}
