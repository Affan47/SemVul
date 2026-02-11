rayTrace(Ray *in, Intersect* output){
    Vector D (in->direction);
    D.unitize();
    Vector N (normal);

    N.unitize();

    Vector W (in->start);
    W.subtract(intersect);

	output->intersect=false;
    if((N.dotProduct(&D) != 0 && W.dotProduct(&N) != 0)){
        double s = -(W.dotProduct(&N)/D.dotProduct(&N));

       if(s>=0){
           Vector intersectMinusCam(0,0,0);
           intersectMinusCam.copy(intersect);
           intersectMinusCam.subtract(in->start);

            if ( !(normal->dotProduct(&intersectMinusCam) <= 0))
                output->normal->setVector(-normal->x,-normal->y,-normal->z);
            else
                output->normal->setVector(normal->x,normal->y,normal->z);

            output->loc->setVector(in->start->x+s*D.x,in->start->y+s*D.y,in->start->z+s*D.z);

            output->view->copy(in->start);
            output->view->subtract(output->loc);

            output->reIntersect(color, s, true);
       }
    }
}
