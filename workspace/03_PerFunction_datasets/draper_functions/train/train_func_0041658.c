BNX2FC_TGT_DBG(const struct bnx2fc_rport *tgt, const char *fmt, ...)
{
	struct va_format vaf;
	va_list args;

	if (likely(!(bnx2fc_debug_level & LOG_TGT)))
		return;

	va_start(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	if (tgt && tgt->port && tgt->port->lport && tgt->port->lport->host &&
	    tgt->rport)
		shost_printk(KERN_INFO, tgt->port->lport->host,
			     PFX "port:%x %pV",
			     tgt->rport->port_id, &vaf);
	else
		pr_info("NULL %pV", &vaf);

	va_end(args);
}
