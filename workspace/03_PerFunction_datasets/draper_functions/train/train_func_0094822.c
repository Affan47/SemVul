init(){
    _xmltag="phon";
    _element_id = Phon_t;
    _annotation_type = AnnotationType::PHON;
    const ElementType accept[] = { Feature_t, Description_t };
    _accepted_data = std::set<ElementType>(accept, accept + 2 );
  }
