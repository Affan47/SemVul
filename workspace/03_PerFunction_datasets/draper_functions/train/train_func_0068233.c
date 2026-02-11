caml_extunixba_write_common(value v_fd, value v_buf, int mode) {
    CAMLparam2(v_fd, v_buf);
    ssize_t ret;
    size_t fd = Int_val(v_fd);
    size_t len = Caml_ba_array_val(v_buf)->dim[0];
    size_t processed = 0;
    char *buf = (char*)Caml_ba_data_val(v_buf);

    while(len > 0) {
	caml_enter_blocking_section();
	ret = write(fd, buf, len);
	caml_leave_blocking_section();
	if (ret == 0) break;
	if (ret == -1) {
	    if (errno == EINTR && (mode & NOINTR)) continue;
	    if (processed > 0){
		if (errno == EAGAIN || errno == EWOULDBLOCK) break;
		if (mode & NOERROR) break;
	    }
	    uerror("write", Nothing);
	}
	processed += ret;
	buf += ret;
	len -= ret;
	if (mode & ONCE) break;
    }

    CAMLreturn(Val_long(processed));
}
