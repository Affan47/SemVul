__ecereNameSpace__eda__ToASCII(unsigned int ch)
{
char asciiCH = (char)0;

if(ch > 127)
{
if(ch == 192 || ch == 193 || ch == 194 || ch == 195 || ch == 196 || ch == 197)
asciiCH = 'A';
else if(ch == 199)
asciiCH = 'C';
else if(ch == 200 || ch == 201 || ch == 202 || ch == 203)
asciiCH = 'E';
else if(ch == 204 || ch == 205 || ch == 206 || ch == 207)
asciiCH = 'I';
else if(ch == 209)
asciiCH = 'N';
else if(ch == 210 || ch == 211 || ch == 212 || ch == 213 || ch == 214)
asciiCH = 'O';
else if(ch == 217 || ch == 218 || ch == 219 || ch == 220)
asciiCH = 'U';
else if(ch == 224 || ch == 225 || ch == 226 || ch == 227 || ch == 228 || ch == 229)
asciiCH = 'a';
else if(ch == 231)
asciiCH = 'c';
else if(ch == 232 || ch == 233 || ch == 234 || ch == 235)
asciiCH = 'e';
else if(ch == 236 || ch == 237 || ch == 238 || ch == 239)
asciiCH = 'i';
else if(ch == 241)
asciiCH = 'n';
else if(ch == 242 || ch == 243 || ch == 244 || ch == 245 || ch == 246)
asciiCH = 'o';
else if(ch == 249 || ch == 250 || ch == 251 || ch == 252)
asciiCH = 'u';
}
else
asciiCH = (char)ch;
return asciiCH;
}
