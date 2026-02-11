init(){
    _xmltag="w";
    _element_id = Word_t;
    const ElementType accept[] = { TextContent_t, Pos_t, Lemma_t,
				   Sense_t, Alternative_t,
				   Correction_t, ErrorDetection_t,
				   Description_t, Morphology_t,
				   Alignment_t, Metric_t };
    _accepted_data = std::set<ElementType>(accept, accept + 11 );
    _annotation_type = AnnotationType::TOKEN;
    TEXTDELIMITER = " ";
    space = true;
  }
