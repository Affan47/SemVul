share()
{


    unsigned int val = m_skill & 0x3F;
    unsigned int counter = 0;

    do
    {
	if(val & 0x01)
	    counter++;

	val = val >> 1;
    }
    while(val);

    unsigned int total = m_num_strings * m_num_chars;
    unsigned int bound = total/counter;

    if(total %  counter)
	bound++;

    return bound;
}
