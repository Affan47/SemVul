extract_from_pes(int fdin, int fdout, uint8_t id, int es)
{
		p2p p;
		int count = 1;
		uint8_t buf[SIZE];

		init_p2p(&p, NULL, 2048);
		p.fd1 = fdout;
		p.filter = id;
		p.es = es;

		while (count > 0){
			count = read(fdin,buf,SIZE);
			get_pes(buf,count,&p,pes_filt);
		}
}
