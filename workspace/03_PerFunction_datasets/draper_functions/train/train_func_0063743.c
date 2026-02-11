mangleCoveragePath(StringRef Filename, bool PreservePaths) {
  if (!PreservePaths)
    return sys::path::filename(Filename).str();


  llvm::SmallString<256> Result("");
  StringRef::iterator I, S, E;
  for (I = S = Filename.begin(), E = Filename.end(); I != E; ++I) {
    if (*I != '/')
      continue;

    if (I - S == 1 && *S == '.') {

    } else if (I - S == 2 && *S == '.' && *(S + 1) == '.') {

      Result.append("^#");
    } else {
      if (S < I)

        Result.append(S, I);

      Result.push_back('#');
    }
    S = I + 1;
  }

  if (S < I)
    Result.append(S, I);
  return Result.str();
}
