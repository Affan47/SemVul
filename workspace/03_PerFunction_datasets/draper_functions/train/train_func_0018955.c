isalpha_pl(unsigned char c)
{

    if(isalpha(c))
	return 1;
    else if(c == 177 || c == 230 || c == 234 || c == 179 || c == 241 || c == 243 || c == 182 || c == 191 || c == 188)
	return 1;
    else if(c == 161 || c == 198 || c == 202 || c == 209 || c == 163 || c == 211 || c == 166 || c == 175 || c == 172)
	return 1;
    else
	return 0;
}
