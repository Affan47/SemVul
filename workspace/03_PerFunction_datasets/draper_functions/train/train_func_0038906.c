getAnnotation() {
  list<int>::iterator ai;

  if (Annotations.empty())
    return 0;

  AnnotationBuffer[0]=0;
  for(ai=Annotations.begin();ai!=Annotations.end();ai++)
    strncat(AnnotationBuffer, global.annotator.get(*ai), 511);

  return(AnnotationBuffer);
}
