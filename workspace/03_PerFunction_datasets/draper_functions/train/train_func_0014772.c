AnimateEnemys (void)
{
  int i;

  for (i = 0; i < NumEnemys; i++)
    {


      if (AllEnemys[i].levelnum != CurLevel->levelnum)
	continue;
      if (AllEnemys[i].status == OUT)
	continue;


      AllEnemys[i].phase +=
	(AllEnemys[i].energy / Druidmap[AllEnemys[i].type].maxenergy) *
	Frame_Time () * ENEMYPHASES * 2.5;

      if (AllEnemys[i].phase >= ENEMYPHASES)
	{
	  AllEnemys[i].phase = 0;
	}
    }
}
