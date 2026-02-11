free_addrinfo(struct addrinfo* ai)
{
	for (struct addrinfo *next, *p = ai; p; p = next) {
		next = p->ai_next;
		delete reinterpret_cast<struct sockaddr_storage*>(p->ai_addr);
		free(p->ai_canonname);
		delete p;
	}
}
