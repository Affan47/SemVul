operator()(z_stream* strm) const {
    deflateEnd(strm);
    delete strm;
  }
}
