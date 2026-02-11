writeNSizResource(NSizResource* data, char* buffer) {
  char itemBuffer[1024];
  char* sha1Buffer;

  (*buffer) = '\0';
  itemBuffer[0] = '\0';

  strcat(buffer, plistHeader);
  if(data->sha1Digest != NULL) {
    sha1Buffer = convertBase64(data->sha1Digest, 20, 1, 42);
    sprintf(itemBuffer, "\t<key>SHA-1-digest</key>\n\t<data>\n%s\t</data>\n", sha1Buffer);
    free(sha1Buffer);
    strcat(buffer, itemBuffer);
  }
  sprintf(itemBuffer, "\t<key>block-checksum-2</key>\n\t<integer>%d</integer>\n", (int32_t)(data->blockChecksum2));
  strcat(buffer, itemBuffer);
  if(data->isVolume) {
    sprintf(itemBuffer, "\t<key>bytes</key>\n\t<integer>%d</integer>\n", (int32_t)(data->bytes));
    strcat(buffer, itemBuffer);
    sprintf(itemBuffer, "\t<key>date</key>\n\t<integer>%d</integer>\n", (int32_t)(data->modifyDate));
    strcat(buffer, itemBuffer);
  }
  sprintf(itemBuffer, "\t<key>part-num</key>\n\t<integer>%d</integer>\n", (int32_t)(data->partitionNumber));
  strcat(buffer, itemBuffer);
  sprintf(itemBuffer, "\t<key>version</key>\n\t<integer>%d</integer>\n", (int32_t)(data->version));
  strcat(buffer, itemBuffer);
  if(data->isVolume) {
    sprintf(itemBuffer, "\t<key>bytes</key>\n\t<integer>%d</integer>\n", (int32_t)(data->volumeSignature));
    strcat(buffer, itemBuffer);
  }
  strcat(buffer, plistFooter);
}
