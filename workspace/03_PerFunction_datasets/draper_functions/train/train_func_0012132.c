flush() {
    if ( shift )
       result += asciiCodingTable[buf & 63];
    result += "#";
 }
