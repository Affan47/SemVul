init(){
    _optional_attributes = ALL;
    _xmltag = "alignment";
    _element_id = Alignment_t;
    const ElementType accept[] = { AlignReference_t, Description_t };
    _accepted_data = std::set<ElementType>(accept, accept + 2 );
    occurrences_per_set=0;
    _annotation_type = AnnotationType::ALIGNMENT;
    PRINTABLE = false;
  }
