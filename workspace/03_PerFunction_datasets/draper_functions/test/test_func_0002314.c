handle_wbands_keypress(int c)
{
    switch (c) {
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case KEY_F(1):
    case KEY_F(2):
    case KEY_F(3):
    case KEY_F(4):
    case KEY_F(5):
    case KEY_F(6):
    case KEY_F(7):
    case KEY_F(8):
	band = (c >= '1' && c <= '8')  ?  c - '1' : c - KEY_F(1);

    case 27:
    case EOF:
    case 'b':
    case 'B':
    case 'e':
    case 'E':
    case 'q':
    case 'Q':
    case 'x':
    case 'X':
	delwin(wbands);
	wbands = NULL;
	redraw();
	break;
    }
}
