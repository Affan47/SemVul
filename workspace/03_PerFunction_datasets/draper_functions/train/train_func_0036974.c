DelObject(dGeomID Object){

	dxGeom* g = First;
	dxGeom* Last = 0;
	while (g){
		if (g == Object){
			if (Last){
				Last->next = g->next;
			}
			else First = g->next;

			break;
		}
		Last = g;
		g = g->next;
	}

	Object->tome = 0;


	Block* Block = this;
	do{
		Block->GeomCount--;
		Block = Block->Parent;
	}
	while (Block);
}
