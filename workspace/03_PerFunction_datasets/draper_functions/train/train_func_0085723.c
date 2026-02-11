K2k(c, n)
     Character *c;
     Character *n;
{
    unsigned char *b;
    int i;

    static unsigned char K2k_table[0x60][3] = {
	"",   "'",  "1",  "(",  "2",  ")",  "3",  "*",
	"4",  "+",  "5",  "6",  "6^", "7",  "7^", "8",
	"8^", "9",  "9^", ":",  ":^", ";",  ";^", "<",
	"<^", "=",  "=^", ">",  ">^", "?",  "?^", "@",
	"@^", "A",  "A^", "/",  "B",  "B^", "C",  "C^",
	"D",  "D^", "E",  "F",  "G",  "H",  "I",  "J",
	"J^", "J_", "K",  "K^", "K_", "L",  "L^", "L_",
	"M",  "M^", "M_", "N",  "N^", "N_", "O",  "P",
	"Q",  "R",  "S",  ",",  "T",  "-",  "U",  ".",
	"V",  "W",  "X",  "Y",  "Z",  "[",  "\\",  "\\",
	"2",  "4",  "&",  "]",  "3^", "6",  "9",   "",
	"",   "",   "",   "",   "",   "",   "",   ""};

    if (c[0].c1 == 0xa5) {
	for (b = K2k_table[(c[0].c2 & 0x7f) - 0x20], i = 0;
	     *b != '\0'; ++ b, ++ i) {
	    n[i].type = KATAKANA;
	    n[i].c1 = *b;
	}
	n[i].type = OTHER;
	n[i].c1 = 0;
    } else if ((c[0].c1 == 0xa1) &&
	       ((c[0].c2 == 0xbc) || (c[0].c2 == 0xab) || (c[0].c2 == 0xac))) {
	n[0].type = KATAKANA;
	switch(c[0].c2) {
	  case 0xbc:
	    n[0].c1 = '0'; break;
	  case 0xab:
	    n[0].c1 = '^'; break;
	  case 0xac:
	    n[0].c1 = '_'; break;
	}
	n[1].type = OTHER;
	n[1].c1 = 0;
    } else {
	n[0].type = OTHER;
	n[0].c1 = 0;
    }
    return 1;
}
