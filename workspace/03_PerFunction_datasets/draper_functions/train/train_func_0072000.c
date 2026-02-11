loescheAusZentralregister() {
  for (int i = 0; i < (int) gAlleBilddateien->size(); i++)
    if ((*gAlleBilddateien)[i] == this) {
      (*gAlleBilddateien)[i] = (*gAlleBilddateien)[gAlleBilddateien->size() - 1];
      gAlleBilddateien->resize(gAlleBilddateien->size() - 1);
      return;
    }
  CASSERT("Internal error in Bilddatei registration");
}
