cap_emulate_setxuid(struct cred *new, const struct cred *old)
{
	kuid_t root_uid = make_kuid(old->user_ns, 0);

	if ((uid_eq(old->uid, root_uid) ||
	     uid_eq(old->euid, root_uid) ||
	     uid_eq(old->suid, root_uid)) &&
	    (!uid_eq(new->uid, root_uid) &&
	     !uid_eq(new->euid, root_uid) &&
	     !uid_eq(new->suid, root_uid))) {
		if (!issecure(SECURE_KEEP_CAPS)) {
			cap_clear(new->cap_permitted);
			cap_clear(new->cap_effective);
		}


		cap_clear(new->cap_ambient);
	}
	if (uid_eq(old->euid, root_uid) && !uid_eq(new->euid, root_uid))
		cap_clear(new->cap_effective);
	if (!uid_eq(old->euid, root_uid) && uid_eq(new->euid, root_uid))
		new->cap_effective = new->cap_permitted;
}
