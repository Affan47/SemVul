princo_(integer obj, integer desc)
{

   integer i;

   rspsub_(desc, objcts_1.odesc2[obj - 1]);

   for (i = 1; i <= objcts_1.olnt; ++i) {

      if (objcts_1.ocan[i - 1] == obj) {
         rspsub_(502, objcts_1.odesc2[i - 1]);
      }

   }
}
