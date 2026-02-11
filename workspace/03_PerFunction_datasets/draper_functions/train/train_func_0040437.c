RearrangeVectors(SYMMETRY *s, VECTOR *vec1,VECTOR *vec2) {
  int problem_flag = FALSE;
  VECTOR tmp;

  if (s->trans == 2) {

    problem_flag = PickTwo(&(s->v1),&(s->v2),vec1,vec2);
    if (problem_flag) {

      AddVector(&(s->v1),&(s->v2),-1,&tmp);
      problem_flag = PickTwo(&(s->v1),&tmp,vec1,vec2);

      if (problem_flag)
	problem_flag = PickTwo(&(s->v2),&tmp,vec1,vec2);
    }


    if (problem_flag)
      printf("Bad! (%f,%f),(%f,%f),(%f,%f) \n",
	     (s->v1).x, (s->v1).y,
	     (s->v2).x, (s->v2).y,
	     tmp.x, tmp.y );


    if (vec1->x < 0.0) VectorScalarMult(vec1,-1.0);
    if (vec2->x < 0.0) VectorScalarMult(vec2,-1.0);

  }
  else {

    *vec1 = (s->v1);
    *vec2 = (s->v2);


    if (!((vec1->x > 0.0) || (vec1->x == 0.0)))
      VectorScalarMult(vec1,-1.0);
    if (!((vec2->x > 0.0) || (vec2->x == 0.0)))
      VectorScalarMult(vec2,-1.0);


  }

}
