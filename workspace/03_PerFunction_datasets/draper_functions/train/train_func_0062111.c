parseFeature() {
    FeaturePtr     feature;
    FeatureLinePtr fline = getUnwrappedFeatureTableLine();

    if (!fline.Null()) {
        if (fline->type != FL_START) throw "Expected feature start";

        feature = new Feature(fline->name, fline->rest);

        fline = getUnwrappedFeatureTableLine();
        while (!fline.Null() && (fline->type & FL_META_QUALIFIER)) {
            feature->addQualifiedEntry(fline->name, fline->rest);
            fline = getUnwrappedFeatureTableLine();
        }
        if (!fline.Null()) backFeatureTableLine(fline);
    }

    return feature;
}
