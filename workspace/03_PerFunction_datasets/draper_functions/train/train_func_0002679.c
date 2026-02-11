Fg()
{
   super::Fg();
   if(input)
      input->Fg();
   if(output && input != output)
      output->Fg();
}
