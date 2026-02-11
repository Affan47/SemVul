getDirectoryListingXml() {
    Log::err("getDirectoryListingXml is not implemented for device "+this->displayName);

    return "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n\
           <DirectoryListing xmlns=\"http://www.garmin.com/xmlschemas/DirectoryListing/v1\" RequestedPath=\"\" UnitId=\"1234567890\" VolumePrefix=\"\"/>";
}
