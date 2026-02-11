checkloinstree (ptnode)

loins_tree *ptnode;


{
 int checkleft, checkright;

 if (ptnode == NULL) return ( OK );

 switch (ptnode->MARK) {
        case BOTH :

             checkleft  = checkloinstree (ptnode->LEFT);
             checkright = checkloinstree (ptnode->RIGHT);
             return ( ((checkleft == OK) && (checkright == OK)) ? OK : ERR );

        case NET1 :

             error_count ++;
             printf ("\nInstance '%s' only in netlist 1", ptnode->LOINS->INSNAME);
             checkloinstree (ptnode->LEFT);
             checkloinstree (ptnode->RIGHT);
             return ( ERR );

        case NET2 :

             error_count ++;
             printf ("\nInstance '%s' only in netlist 2", ptnode->LOINS->INSNAME);
             checkloinstree (ptnode->LEFT);
             checkloinstree (ptnode->RIGHT);
             return ( ERR );
        }

 fatalerror ("Fatal error on Instances Tree checking. (checkloinstree)");
}
