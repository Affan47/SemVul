apply(const plan *ego_, R *I, R *O)
{
     const P *ego = (const P *) ego_;
     plan_rdft *cld1, *cld2;


     cld1 = (plan_rdft *) ego->cld1;
     if (ego->preserve_input) {
	  cld1->apply(ego->cld1, I, O);
	  I = O;
     }
     else
	  cld1->apply(ego->cld1, I, I);


     cld2 = (plan_rdft *) ego->cld2;
     cld2->apply(ego->cld2, I, O);
}
