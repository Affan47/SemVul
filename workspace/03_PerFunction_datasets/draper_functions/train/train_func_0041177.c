Encode(MutableFstClass *ofst, uint32 flags, bool reuse_encoder,
            const string &coder_fname) {
  EncodeArgs args(ofst, flags, reuse_encoder, coder_fname);

  Apply<Operation<EncodeArgs> >("Encode", ofst->ArcType(), &args);
}
