do_it(CS& cmd, CARD_LIST*)
  {itested();
    static std::list<FILE*> filestack;

    if (cmd.more()) {
      const char* access = "w";
      while (cmd.match1('>')) {
	access = "a";
	cmd.skip();
	cmd.skipbl();
      }
      FILE* newfile = xopen(cmd,"",access);
      if (newfile) {
	filestack.push_back(newfile);
	mout.attach(newfile);
	IO::mstdout.attach(newfile);
      }else{
      }
    }else{
      if (filestack.empty()) {
	error(bWARNING, "no files open\n");
      }else{
	FILE* oldfile = filestack.back();
	filestack.pop_back();
	mout.detach(oldfile);
	IO::mstdout.detach(oldfile);
	fclose(oldfile);
      }
    }
  }
}
