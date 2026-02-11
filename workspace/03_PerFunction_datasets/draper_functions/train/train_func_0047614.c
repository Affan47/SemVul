kc_casestrhash
#ifdef KC_USE_PROTOTYPES
(char *kc_s)
#else
(kc_s) char *kc_s;
#endif
{	register unsigned kc_i = 0;
	register char *kc_sp;

	for (kc_sp = kc_s; *kc_sp != '\0'; kc_sp++)
		kc_i = (unsigned)((kc_i * 75) + *kc_sp);
	return kc_i;
}
