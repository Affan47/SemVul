inspect(
      const string & library_name,
      const path & full_path,
      const string & contents )
    {
      if (contents.find( "boostinspect:" "noend" ) != string::npos) return;


      const char test_file_name[] = "wrong_line_ends_test.cpp";

      char final_char = contents.begin() == contents.end() ? '\0'
        : *(boost::prior(contents.end()));

      bool failed = final_char != '\n' && final_char != '\r';

      if (failed && full_path.leaf() != test_file_name)
      {
        ++m_files_with_errors;
        error( library_name, full_path, string(name()) + ' ' + desc() );
      }

      if (!failed && full_path.leaf() == test_file_name)
      {
        ++m_files_with_errors;
        error( library_name, full_path, string(name()) + " should not end with a newline" );
      }
    }
