getTrimmedTrailer()
{


    QPDFObjectHandle trailer = pdf.getTrailer().shallowCopy();


    trailer.removeKey("/ID");
    trailer.removeKey("/Encrypt");


    trailer.removeKey("/Prev");


    trailer.removeKey("/Index");
    trailer.removeKey("/W");
    trailer.removeKey("/Length");
    trailer.removeKey("/Filter");
    trailer.removeKey("/DecodeParms");
    trailer.removeKey("/Type");
    trailer.removeKey("/XRefStm");

    return trailer;
}
