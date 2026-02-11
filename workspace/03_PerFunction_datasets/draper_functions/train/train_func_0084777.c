prettyPrint() const
    {
        QTextStream out(stdout, QIODevice::WriteOnly);
        out << "File " << baseName << " version " << version[0] << version[1];
        out << "\n cached bytes     " << bytesCached << " useCount " << useCount;
        out << "\n servedDate       " << dateString(servedDate);
        out << "\n lastModifiedDate " << dateString(lastModifiedDate);
        out << "\n expireDate       " << dateString(expireDate);
        out << "\n entity tag       " << etag;
        out << "\n encoded URL      " << url;
        out << "\n mimetype         " << mimeType;
        out << "\nResponse headers follow...\n";
        Q_FOREACH (const QString &h, responseHeaders) {
            out << h << '\n';
        }
    }
}
