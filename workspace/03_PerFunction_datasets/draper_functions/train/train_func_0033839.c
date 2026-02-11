insig(base64_input &inchar)
{
    int c;


    while (TRUE) {
	c = inchar();
        if (c == EOF || (c > ' ')) {
	    return c;
	}
    }

}
