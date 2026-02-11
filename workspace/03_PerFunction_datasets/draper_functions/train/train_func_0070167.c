TagPosition_ (int *tag_screen_left_xP,
		  int *tag_screen_right_xP,
		  int *tag_screen_yP,
		  MolComplexS *curr_mol_complexSP,
		  int imagesN)
{
size_t		atomsN, atomI;
AtomS		*curr_atomSP;
int		screen_left_x_min, screen_left_x_max;
int		screen_right_x_min = 0, screen_right_x_max = 0;
int		screen_y_min, screen_y_max;
int		screen_left_x, screen_right_x, screen_y;


atomsN = curr_mol_complexSP->atomsN;
if (atomsN == 0) return 0;


screen_left_x_min = curr_mol_complexSP->atomSP->raw_atomS.screen_x[0];
screen_left_x_max = screen_left_x_min;
screen_y_min      = curr_mol_complexSP->atomSP->raw_atomS.screen_y;
screen_y_max      = screen_y_min;
if (imagesN == 2)
	{
	screen_right_x_min = curr_mol_complexSP->atomSP->raw_atomS.screen_x[1];
	screen_right_x_max = screen_right_x_min;
	}


for (atomI = 1; atomI < atomsN; atomI++)
	{

	curr_atomSP = curr_mol_complexSP->atomSP + atomI;


	screen_left_x = curr_atomSP->raw_atomS.screen_x[0];
	screen_y      = curr_atomSP->raw_atomS.screen_y;
	if (screen_left_x < screen_left_x_min)
		{
		screen_left_x_min = screen_left_x;
		}
	if (screen_left_x > screen_left_x_max)
		{
		screen_left_x_max = screen_left_x;
		}
	if (screen_y < screen_y_min) screen_y_min = screen_y;
	if (screen_y > screen_y_max) screen_y_max = screen_y;
	if (imagesN == 2)
		{
		screen_right_x = curr_atomSP->raw_atomS.screen_x[1];
		if (screen_right_x < screen_right_x_min)
			{
			screen_right_x_min = screen_right_x;
			}
		if (screen_right_x > screen_right_x_max)
			{
			screen_right_x_max = screen_right_x;
			}
		}
	}


*tag_screen_left_xP  = (screen_left_x_min  + screen_left_x_max)  / 2;
*tag_screen_right_xP = (screen_right_x_min + screen_right_x_max) / 2;
*tag_screen_yP       = screen_y_min;


return 1;
}
