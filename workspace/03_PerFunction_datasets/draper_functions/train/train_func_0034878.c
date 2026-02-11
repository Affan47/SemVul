AverageAffineTransform( std::vector<std::string> args, std::ostream* )
{


  args.insert( args.begin(), "AverageAffineTransform" );
  int     argc = args.size();
  char* * argv = new char *[args.size() + 1];
  for( unsigned int i = 0; i < args.size(); ++i )
    {

    argv[i] = new char[args[i].length() + 1];
    std::strncpy( argv[i], args[i].c_str(), args[i].length() );

    argv[i][args[i].length()] = '\0';
    }
  argv[argc] = 0;

  class Cleanup_argv
  {
public:
    Cleanup_argv( char* * argv_, int argc_plus_one_ ) : argv( argv_ ), argc_plus_one( argc_plus_one_ )
    {
    }

    ~Cleanup_argv()
    {
      for( unsigned int i = 0; i < argc_plus_one; ++i )
        {
        delete[] argv[i];
        }
      delete[] argv;
    }

private:
    char* *      argv;
    unsigned int argc_plus_one;
  };
  Cleanup_argv cleanup_argv( argv, argc + 1 );


  if( argc <= 3 )
    {
    std::cerr
      << "AverageAffineTransform ImageDimension output_affine_transform [-R reference_affine_transform] "
      << "{[-i] affine_transform_txt [weight(=1)] ]}"
      << std::endl
      << std::endl
      << " Usage: Compute weighted average of input affine transforms. "
      << std::endl
      << "For 2D and 3D transform, the affine transform is first decomposed into "
      "scale x shearing x rotation. Then these parameters are averaged, using the weights if they provided. "
      "For 3D transform, the rotation component is the quaternion. After averaging, the quaternion will also "
      "be normalized to have unit norm. For 2D transform, the rotation component is the rotation angle. "
      "The weight for each transform is a non-negative number. The sum of all weights will be normalized to 1 "
      "before averaging. The default value for each weight is 1.0. "
      << std::endl
      << std::endl
      << "All affine transforms is a \"centerd\" transform, following ITK convention. A reference_affine_transform"
      " defines the center for the output transform. The first provided transform is the default reference "
      "transform"
      << std::endl
      << "Output affine transform is a MatrixOffsetBaseTransform."
      << std::endl
      << " -i option takes the inverse of the affine mapping."
      << std::endl
      << " For example: "
      << std::endl
      << " 2 output_affine.txt -R A.txt A1.txt 1.0 -i A2.txt 2.0 A3.txt A4.txt 6.0 A5.txt"
      << std::endl
      << "This computes: (1*A1 + 2*(A2)^-1 + A3 + A4*6 + A5 ) / (1+2+1+6+5)"
      << std::endl;
    return EXIT_SUCCESS;
    }

  TRAN_OPT_QUEUE opt_queue;

  char *output_transform_filename = NULL;
  char *reference_transform_filename = NULL;

  int  kImageDim = atoi(argv[1]);

  const bool is_parsing_ok = AverageAffineTransform_ParseInput(argc - 2, argv + 2, output_transform_filename,
                                                    reference_transform_filename, opt_queue);

  if( is_parsing_ok )
    {
    std::cout << "output_transform_filename: " << output_transform_filename
             << std::endl;
    std::cout << "reference_transform_filename: ";

    if( reference_transform_filename )
      {
      std::cout << reference_transform_filename << std::endl;
      }
    else
      {
      std::cout << "NULL" << std::endl;
      }

    DisplayOptQueue(opt_queue);

    switch( kImageDim )
      {
      case 2:
        {
        AverageAffineTransform<2>(output_transform_filename,
                                  reference_transform_filename, opt_queue);
        }
        break;
      case 3:
        {
        AverageAffineTransform<3>(output_transform_filename,
                                  reference_transform_filename, opt_queue);
        }
        break;
      }
    }

  else
    {
    std::cerr << "Input error!" << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
