vimostanset(prj)

struct prjprm *prj;

{
   if (prj->r0 == 0.0) prj->r0 = R2D;

   if (prj->flag == -1) {
      prj->flag = -PRJSET;
   } else {
      prj->flag = PRJSET;
   }

   return 0;
}
