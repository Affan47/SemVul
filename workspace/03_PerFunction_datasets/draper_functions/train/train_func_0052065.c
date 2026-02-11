gspool_ptrfind(const int fd, const unsigned flags, const char *name, const netid_t nid, slotno_t *slotno, struct apispptr *result)
{
	int		ret;
	struct	api_fd	*fdp = gspool_look_fd(fd);
	struct	api_msg		msg;
	char	ptrname[PTRNAMESIZE+1];

	if  (!fdp)
		return  GSPOOL_INVALID_FD;

	strncpy(ptrname, name, PTRNAMESIZE);
	ptrname[PTRNAMESIZE] = '\0';

	msg.code = API_FINDPTR;
	msg.un.ptrfind.flags = htonl(flags);
	msg.un.ptrfind.netid = nid;
	if  ((ret = gspool_wmsg(fdp, &msg)))
		return  ret;
	if  ((ret = gspool_write(fdp->sockfd, ptrname, sizeof(ptrname))))
		return  ret;
	if  ((ret = gspool_rmsg(fdp, &msg)))
		return  ret;
	if  (msg.un.r_find.seq != 0)
		fdp->pserial = ntohl(msg.un.r_find.seq);
	if  (msg.retcode != 0)
		return  (SHORT) ntohs(msg.retcode);
	if  (slotno)
		*slotno = ntohl(msg.un.r_find.slotno);
	return  ptr_readrest(fdp, result);
}
