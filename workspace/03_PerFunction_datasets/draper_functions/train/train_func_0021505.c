color_names_destroy(ColorNames* cnames)
{
	for (list<ColorNameEntry*>::iterator i=cnames->names.begin();i!=cnames->names.end();++i){
		delete (*i);
	}
	for (int x=0;x<8;x++){
		for (int y=0;y<8;y++){
			for (int z=0;z<8;z++){
				for (list<ColorEntry*>::iterator i=cnames->colors[x][y][z].begin();i!=cnames->colors[x][y][z].end();++i){
					delete (*i);
				}
			}
		}
	}
	delete cnames;
}
