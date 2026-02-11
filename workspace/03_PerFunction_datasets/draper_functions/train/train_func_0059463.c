MtxOrb_icon (Driver *drvthis, int x, int y, int icon)
{
	static unsigned char heart_open[] =
		{ b__XXXXX,
		  b__X_X_X,
		  b_______,
		  b_______,
		  b_______,
		  b__X___X,
		  b__XX_XX,
		  b__XXXXX };
	static unsigned char heart_filled[] =
		{ b__XXXXX,
		  b__X_X_X,
		  b___X_X_,
		  b___XXX_,
		  b___XXX_,
		  b__X_X_X,
		  b__XX_XX,
		  b__XXXXX };
	static unsigned char arrow_up[] =
		{ b____X__,
		  b___XXX_,
		  b__X_X_X,
		  b____X__,
		  b____X__,
		  b____X__,
		  b____X__,
		  b_______ };
	static unsigned char arrow_down[] =
		{ b____X__,
		  b____X__,
		  b____X__,
		  b____X__,
		  b__X_X_X,
		  b___XXX_,
		  b____X__,
		  b_______ };


	static unsigned char checkbox_off[] =
		{ b_______,
		  b_______,
		  b__XXXXX,
		  b__X___X,
		  b__X___X,
		  b__X___X,
		  b__XXXXX,
		  b_______ };
	static unsigned char checkbox_on[] =
		{ b____X__,
		  b____X__,
		  b__XXX_X,
		  b__X_XX_,
		  b__X_X_X,
		  b__X___X,
		  b__XXXXX,
		  b_______ };
	static unsigned char checkbox_gray[] =
		{ b_______,
		  b_______,
		  b__XXXXX,
		  b__X_X_X,
		  b__XX_XX,
		  b__X_X_X,
		  b__XXXXX,
		  b_______ };


	switch (icon) {
		case ICON_BLOCK_FILLED:
			MtxOrb_chr(drvthis, x, y, 255);
			break;
		case ICON_HEART_FILLED:
			MtxOrb_set_char(drvthis, 0, heart_filled);
			MtxOrb_chr(drvthis, x, y, 0);
			break;
		case ICON_HEART_OPEN:
			MtxOrb_set_char(drvthis, 0, heart_open);
			MtxOrb_chr(drvthis, x, y, 0);
			break;
		case ICON_ARROW_UP:
			MtxOrb_set_char(drvthis, 1, arrow_up);
			MtxOrb_chr(drvthis, x, y, 1);
			break;
		case ICON_ARROW_DOWN:
			MtxOrb_set_char(drvthis, 2, arrow_down);
			MtxOrb_chr(drvthis, x, y, 2);
			break;
		case ICON_ARROW_LEFT:
			MtxOrb_chr(drvthis, x, y, 0x7F);
			break;
		case ICON_ARROW_RIGHT:
			MtxOrb_chr(drvthis, x, y, 0x7E);
			break;
		case ICON_CHECKBOX_OFF:
			MtxOrb_set_char(drvthis, 3, checkbox_off);
			MtxOrb_chr(drvthis, x, y, 3);
			break;
		case ICON_CHECKBOX_ON:
			MtxOrb_set_char(drvthis, 4, checkbox_on);
			MtxOrb_chr(drvthis, x, y, 4);
			break;
		case ICON_CHECKBOX_GRAY:
			MtxOrb_set_char(drvthis, 5, checkbox_gray);
			MtxOrb_chr(drvthis, x, y, 5);
			break;
		default:
			return -1;
	}
	return 0;
}
