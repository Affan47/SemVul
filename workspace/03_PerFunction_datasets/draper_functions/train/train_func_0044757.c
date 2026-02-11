free_work
(
    WorkType *Work
)
{
    DEBUG0 (("work free:\n")) ;
    if (Work)
    {

	Work->Wx = (Entry *) UMF_free ((void *) Work->Wx) ;
	Work->Wy = (Entry *) UMF_free ((void *) Work->Wy) ;
	Work->Frpos = (Int *) UMF_free ((void *) Work->Frpos) ;
	Work->Fcpos = (Int *) UMF_free ((void *) Work->Fcpos) ;
	Work->Lpattern = (Int *) UMF_free ((void *) Work->Lpattern) ;
	Work->Upattern = (Int *) UMF_free ((void *) Work->Upattern) ;
	Work->Wp = (Int *) UMF_free ((void *) Work->Wp) ;
	Work->Wrp = (Int *) UMF_free ((void *) Work->Wrp) ;
	Work->Frows = (Int *) UMF_free ((void *) Work->Frows) ;
	Work->Fcols = (Int *) UMF_free ((void *) Work->Fcols) ;
	Work->Wio = (Int *) UMF_free ((void *) Work->Wio) ;
	Work->Woi = (Int *) UMF_free ((void *) Work->Woi) ;
	Work->Woo = (Int *) UMF_free ((void *) Work->Woo) ;
	Work->Wm = (Int *) UMF_free ((void *) Work->Wm) ;
	Work->E = (Int *) UMF_free ((void *) Work->E) ;
	Work->Front_new1strow =
	    (Int *) UMF_free ((void *) Work->Front_new1strow) ;


	Work->Diagonal_map = (Int *) UMF_free ((void *) Work->Diagonal_map) ;
	Work->Diagonal_imap = (Int *) UMF_free ((void *) Work->Diagonal_imap) ;
    }
    DEBUG0 (("work free done.\n")) ;
}
