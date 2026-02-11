SplineFontFree(SplineFont *sf) {
    int i;
    BDFFont *bdf, *bnext;

    if ( sf==NULL )
return;
    if ( sf->mm!=NULL ) {
	MMSetFree(sf->mm);
return;
    }
    CopyBufferClearCopiedFrom(sf);
    PasteRemoveSFAnchors(sf);
    for ( bdf = sf->bitmaps; bdf!=NULL; bdf = bnext ) {
	bnext = bdf->next;
	BDFFontFree(bdf);
    }
    for ( i=0; i<sf->glyphcnt; ++i ) if ( sf->glyphs[i]!=NULL )
	SplineCharFree(sf->glyphs[i]);
    free(sf->glyphs);
    free(sf->fontname);
    free(sf->fullname);
    free(sf->familyname);
    free(sf->weight);
    free(sf->copyright);
    free(sf->comments);
    free(sf->filename);
    free(sf->origname);
    free(sf->autosavename);
    free(sf->version);
    free(sf->xuid);
    free(sf->cidregistry);
    free(sf->ordering);
    MacFeatListFree(sf->features);

    SplinePointListsFree(sf->grid.splines);
    AnchorClassesFree(sf->anchor);
    TtfTablesFree(sf->ttf_tables);
    TtfTablesFree(sf->ttf_tab_saved);
    UndoesFree(sf->grid.undoes);
    UndoesFree(sf->grid.redoes);
    PSDictFree(sf->private);
    TTFLangNamesFree(sf->names);
    for ( i=0; i<sf->subfontcnt; ++i )
	SplineFontFree(sf->subfonts[i]);
    free(sf->subfonts);
    GlyphHashFree(sf);
    OTLookupListFree(sf->gpos_lookups);
    OTLookupListFree(sf->gsub_lookups);
    KernClassListFree(sf->kerns);
    KernClassListFree(sf->vkerns);
    FPSTFree(sf->possub);
    ASMFree(sf->sm);
    OtfNameListFree(sf->fontstyle_name);
    OtfFeatNameListFree(sf->feat_names);
    MarkClassFree(sf->mark_class_cnt,sf->mark_classes,sf->mark_class_names);
    MarkSetFree(sf->mark_set_cnt,sf->mark_sets,sf->mark_set_names);
    free( sf->gasp );
#if defined(_NO_PYTHON)
    free( sf->python_persistent );
#else
    PyFF_FreeSF(sf);
#endif
    BaseFree(sf->horiz_base);
    BaseFree(sf->vert_base);
    JustifyFree(sf->justify);
    free(sf);
}
