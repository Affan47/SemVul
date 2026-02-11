ExplodeBlasts (void)
{
  int i;
  Blast CurBlast = AllBlasts;

  for (i = 0; i < MAXBLASTS; i++, CurBlast++)
    if (CurBlast->type != OUT)
      {


	if (CurBlast->type == DRUIDBLAST)
	  CheckBlastCollisions (i);


	CurBlast->phase += Frame_Time () * Blastmap[ CurBlast->type ].phases / Blastmap[ CurBlast->type ].total_animation_time;
	if (((int) floorf (CurBlast->phase)) >=
	    Blastmap[CurBlast->type].phases)
	  DeleteBlast (i);
      }
}
