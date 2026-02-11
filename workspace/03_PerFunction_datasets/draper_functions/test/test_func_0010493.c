reset() {
    cesIndex = ceBuffer.length = 0;
    if(skipped != NULL) { skipped->clear(); }
}
