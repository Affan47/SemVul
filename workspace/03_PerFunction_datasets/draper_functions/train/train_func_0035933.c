uf_close(unit)

int 	*unit;

{
	if ( close( lun2fd[*unit-1] ) < 0 ) {
		return(errno);
	}
	else {
		lun2reclen[*unit-1] = -1;
		return(0);
	}

}
