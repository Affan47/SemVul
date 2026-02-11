operator= (Netbuffer const &other) {
    debugmsg(Mstr("Netbuffer: copying other\n"));
    if (this != &other) {
	destroy();
	copy (other);
    }
    return (*this);
}
