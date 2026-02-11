closeVolume(Volume *volume) {
  if(volume->attrTree)
    closeBTree(volume->attrTree);

  CLOSE(volume->allocationFile);
  closeBTree(volume->catalogTree);
  closeBTree(volume->extentsTree);
  free(volume->volumeHeader);
  free(volume);
}
