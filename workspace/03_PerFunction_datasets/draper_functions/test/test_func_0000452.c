inv_interlace_line(int height, int line)

{

    if ((line << 3)<height) {
	return line << 3;
    }
    line -= (height+7) >> 3;
    if ((line << 3) + 4 < height) {
	return (line << 3) + 4;
    }
    line -= (height+3) >> 3;
    if ((line << 2) + 2 < height) {
	return (line << 2) + 2;
    }
    line -= (height + 1) >> 2;
    return (line << 1) + 1;

}
