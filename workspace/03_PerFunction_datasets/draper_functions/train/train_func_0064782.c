dummy_pseudos(col, totpseudo)
struct working *col;
double totpseudo;
{
   int aa;

   col->totreg = totpseudo;
   for (aa=0; aa<AASALL; aa++) col->reg[aa] = 0.0;
   for (aa=1; aa < AAS; aa++) col->reg[aa] = totpseudo * frequency[aa];

}
