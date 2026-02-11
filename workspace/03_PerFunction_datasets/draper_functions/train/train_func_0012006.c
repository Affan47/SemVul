operator=(const NETRootInfo &rootinfo) {

#ifdef   NETWMDEBUG
    fprintf(stderr, "NETRootInfo::operator=()\n");
#endif

    if (p != rootinfo.p) {
	refdec_nri(p);

	if (! p->ref) delete p;
    }

    p = rootinfo.p;
    p->ref++;

    return *this;
}
