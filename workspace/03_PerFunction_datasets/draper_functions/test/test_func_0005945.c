drawLife(ExploType type)
{
	float	age;
	float	ex, ey;
	float	*p;
	float	clr[4] = { 1.0, 1.0, 1.0, 1.0 };
	float	tmp;
	Explo	*thisExplo;

	glBindTexture(GL_TEXTURE_2D, tex[type]);
	thisExplo = exploRoot[type]->next;
	glBegin(GL_QUADS);
	while(thisExplo)
	{
		age = thisExplo->age*game->speedAdj;
		if(age >= 0)
		{
			p = thisExplo->pos;
			tmp = age/exploStay[type];
			if(type == AddLife)
			{
				clr[0] = clr[1] = tmp;
				clr[2] = 1.0;
				clr[3] = tmp+0.2;
				tmp = 1.0-tmp;
			}
			else if(type == LoseLife)
			{
				clr[0] = 1.0;
				clr[1] = clr[2] = 0.1;
				clr[3] = 1.0-tmp;
			}
			else
			{
				clr[0] = clr[1] = clr[2] = 1.0;
				clr[3] = 1.0-tmp;
			}
			ex = thisExplo->size*exploSize[type][0]*tmp;
			ey = thisExplo->size*exploSize[type][1]*tmp;
			glColor4fv(clr);
			glTexCoord2f(0.0, 1.0); glVertex3f(p[0]-ex, p[1]+ey, p[2]);
			glTexCoord2f(0.0, 0.0); glVertex3f(p[0]-ex, p[1]-ey, p[2]);
			glTexCoord2f(1.0, 0.0); glVertex3f(p[0]+ex, p[1]-ey, p[2]);
			glTexCoord2f(1.0, 1.0); glVertex3f(p[0]+ex, p[1]+ey, p[2]);
		}

		thisExplo = thisExplo->next;
	}
	glEnd();

}
