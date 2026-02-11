findXmp(size_t& xmpPos, size_t& xmpSize, const byte* data, size_t startPos, size_t size, bool write)
    {

        xmpSize = 0;
        for (xmpPos = startPos; xmpPos < size; xmpPos++) {
            if (data[xmpPos] != '\x00' && data[xmpPos] != '<') continue;
            for (size_t i = 0; i < (sizeof xmpHeaders) / (sizeof *xmpHeaders); i++) {
                const std::string &header = xmpHeaders[i];
                if (xmpPos + header.size() > size) continue;
                if (memcmp(data + xmpPos, header.data(), header.size()) != 0) continue;
                #ifdef DEBUG
                EXV_DEBUG << "findXmp: Found XMP header at position: " << xmpPos << "\n";
                #endif


                for (size_t trailerPos = xmpPos + header.size(); trailerPos < size; trailerPos++) {
                    if (data[xmpPos] != '\x00' && data[xmpPos] != '<') continue;
                    for (size_t j = 0; j < (sizeof xmpTrailers) / (sizeof *xmpTrailers); j++) {
                        const std::string &trailer = xmpTrailers[j].trailer;
                        const bool readOnly = xmpTrailers[j].readOnly;

                        if (trailerPos + trailer.size() > size) continue;
                        if (memcmp(data + trailerPos, trailer.data(), trailer.size()) != 0) continue;
                        #ifdef DEBUG
                        EXV_DEBUG << "findXmp: Found XMP trailer at position: " << trailerPos << "\n";
                        #endif

                        if (readOnly) {
                            #ifndef SUPPRESS_WARNINGS
                            EXV_WARNING << "Unable to handle read-only XMP metadata yet. Please provide your "
                                           "sample EPS file to the Exiv2 project: http://dev.exiv2.org/projects/exiv2\n";
                            #endif
                            throw Error(write ? 21 : 14);
                        }


                        for (size_t trailerEndPos = trailerPos + trailer.size(); trailerEndPos + xmpTrailerEnd.size() <= size; trailerEndPos++) {
                            if (memcmp(data + trailerEndPos, xmpTrailerEnd.data(), xmpTrailerEnd.size()) == 0) {
                                xmpSize = (trailerEndPos + xmpTrailerEnd.size()) - xmpPos;
                                return;
                            }
                        }
                        #ifndef SUPPRESS_WARNINGS
                        EXV_WARNING << "Found XMP header but incomplete XMP trailer.\n";
                        #endif
                        throw Error(write ? 21 : 14);
                    }
                }
                #ifndef SUPPRESS_WARNINGS
                EXV_WARNING << "Found XMP header but no XMP trailer.\n";
                #endif
                throw Error(write ? 21 : 14);
            }
        }
    }
